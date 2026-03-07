"""
Simple behavioral I2C models for Renode Habilis board emulation.
Compatible with Renode's IronPython runtime.
"""

import time
from System import Byte
from System import Array

try:
    _integer_types = (int, long)
except NameError:
    _integer_types = (int,)


def _now_seconds():
    if hasattr(time, "monotonic"):
        return time.monotonic()
    return time.time()


def _to_bytes(data):
    if data is None:
        return []
    if isinstance(data, _integer_types):
        return [int(data) & 0xFF]
    try:
        return [int(b) & 0xFF for b in data]
    except Exception:
        return [int(data) & 0xFF]


def _enqueue_bytes(dummy, data):
    buf = [int(b) & 0xFF for b in data]
    dummy.EnqueueResponseBytes(Array[Byte](buf))


def _resolve_dummy(mon, path):
    candidates = [path]
    if not path.startswith("sysbus."):
        candidates.append("sysbus.{0}".format(path))
    if not path.startswith("i2c1."):
        candidates.append("i2c1.{0}".format(path))
    if not path.startswith("sysbus.i2c1."):
        candidates.append("sysbus.i2c1.{0}".format(path))

    if mon is not None and hasattr(mon, "Machine") and mon.Machine is not None:
        for c in candidates:
            try:
                n = mon.Machine[c]
                if n is not None:
                    return n
            except Exception:
                pass

    ext = globals().get("externals")
    if ext is not None:
        for c in candidates:
            try:
                n = ext[c]
                if n is not None:
                    return n
            except Exception:
                pass

    return None


class PCA9685Model(object):
    def __init__(self, dummy):
        self.dummy = dummy
        self.regs = [0] * 256
        self.regs[0x00] = 0x01  # MODE1
        self.regs[0x01] = 0x04  # MODE2
        self.ptr = 0

    def _enqueue_from_ptr(self, count):
        out = []
        p = self.ptr
        for _ in range(count):
            out.append(self.regs[p])
            p = (p + 1) & 0xFF
        _enqueue_bytes(self.dummy, out)

    def write(self, data):
        buf = _to_bytes(data)
        if len(buf) == 0:
            return

        self.ptr = buf[0]
        for b in buf[1:]:
            self.regs[self.ptr] = b
            self.ptr = (self.ptr + 1) & 0xFF

        # Prime response FIFO for possible immediate read transaction.
        self._enqueue_from_ptr(32)


class ADS1110Model(object):
    def __init__(self, dummy):
        self.dummy = dummy
        self.config = 0x8C
        self.sample = 0
        self.direction = 1
        self.last_update = _now_seconds()
        self._refill(256)

    def _period_seconds(self):
        dr = (self.config >> 2) & 0x3
        rates = [15.0, 30.0, 60.0, 240.0]
        return 1.0 / rates[dr]

    def _advance(self):
        now = _now_seconds()
        elapsed = now - self.last_update
        period = self._period_seconds()
        if elapsed < period:
            return

        steps = int(elapsed / period)
        if steps < 1:
            steps = 1

        for _ in range(steps):
            self.sample += self.direction * 73
            if self.sample >= 0x7FFF:
                self.sample = 0x7FFF
                self.direction = -1
            elif self.sample <= 0:
                self.sample = 0
                self.direction = 1

        self.last_update = now

    def _frame(self):
        self._advance()
        raw = self.sample & 0xFFFF
        drdy = 1 if (_now_seconds() - self.last_update) <= self._period_seconds() else 0
        cfg = ((drdy & 0x1) << 7) | (self.config & 0x7F)
        return [(raw >> 8) & 0xFF, raw & 0xFF, cfg]

    def _refill(self, frames):
        out = []
        for _ in range(frames):
            out.extend(self._frame())
        _enqueue_bytes(self.dummy, out)

    def write(self, data):
        buf = _to_bytes(data)
        if len(buf) > 0:
            # ADS1110 writable config is low 7 bits.
            self.config = buf[-1] & 0x7F

        # Top-up response FIFO after config writes.
        self._refill(128)


class EEPROM24C04AModel(object):
    def __init__(self, dummy):
        self.dummy = dummy
        self.mem = [0xFF] * 512
        self.ptr = 0

    def _enqueue_from_ptr(self, count):
        out = []
        p = self.ptr
        for _ in range(count):
            out.append(self.mem[p])
            p = (p + 1) % len(self.mem)
        _enqueue_bytes(self.dummy, out)

    def write(self, data):
        buf = _to_bytes(data)
        if len(buf) == 0:
            return

        self.ptr = buf[0] % len(self.mem)
        for b in buf[1:]:
            self.mem[self.ptr] = b
            self.ptr = (self.ptr + 1) % len(self.mem)

        self._enqueue_from_ptr(64)


def setup_peripherals(_monitor, pca_path, ads_path, eep_path):
    pca = _resolve_dummy(_monitor, pca_path)
    ads = _resolve_dummy(_monitor, ads_path)
    eep = _resolve_dummy(_monitor, eep_path)

    if pca is None or ads is None or eep is None:
        raise RuntimeError("Cannot resolve one or more I2C dummy peripherals")

    pca.DataReceived += PCA9685Model(pca).write
    ads.DataReceived += ADS1110Model(ads).write
    eep.DataReceived += EEPROM24C04AModel(eep).write
