//
// Created by pouyan on 4/14/26.
//

#pragma once

#include <memory>
#include <map>

#include <rebel/io/reader.hpp>

#include <habilis/io/dev/i2c.hpp>

namespace Habilis {
    class ADS1115 : public Rebel::Reader<float> {
    public:
        explicit ADS1115(std::unique_ptr<I2C_Slot> device, short int channel);

        float read() override;

    private:
        // -----------------
        //  Write registers
        // -----------------

        static constexpr unsigned short int ADDR_CONVERSION{0b00}; // Conversion register
        static constexpr unsigned short int ADDR_CONFIG{0b01}; // Config register
        static constexpr unsigned short int ADDR_LOW_THRESHOLD{0b10}; // Low threshold register
        static constexpr unsigned short int ADDR_HIGH_THRESHOLD{0b11}; // High threshold register

        static constexpr unsigned int CFG_OS_START{0b1UL << 15}; // Start a single conversion (when in power-down state)

        static constexpr unsigned int CFG_MUX_A0_A1{0b000UL << 12}; // AINP = AIN0 and AINN = AIN1 (default)
        static constexpr unsigned int CFG_MUX_A0_A3{0b001UL << 12}; // AINP = AIN0 and AINN = AIN3
        static constexpr unsigned int CFG_MUX_A1_A3{0b010UL << 12}; // AINP = AIN1 and AINN = AIN3
        static constexpr unsigned int CFG_MUX_A2_A3{0b011UL << 12}; // AINP = AIN2 and AINN = AIN3
        static constexpr unsigned int CFG_MUX_A0_GND{0b100UL << 12}; // AINP = AIN0 and AINN = GND
        static constexpr unsigned int CFG_MUX_A1_GND{0b101UL << 12}; // AINP = AIN1 and AINN = GND
        static constexpr unsigned int CFG_MUX_A2_GND{0b110UL << 12}; // AINP = AIN2 and AINN = GND
        static constexpr unsigned int CFG_MUX_A3_GND{0b111UL << 12}; // AINP = AIN3 and AINN = GND

        static constexpr unsigned short int CFG_PGA_POS{9};
        static constexpr unsigned int CFG_PGA_6_144{0b000UL << CFG_PGA_POS}; // FSR = ±6.144 V
        static constexpr unsigned int CFG_PGA_4_096{0b001UL << CFG_PGA_POS}; // FSR = ±4.096 V
        static constexpr unsigned int CFG_PGA_2_048{0b010UL << CFG_PGA_POS}; // FSR = ±2.048 V (default)
        static constexpr unsigned int CFG_PGA_1_024{0b011UL << CFG_PGA_POS}; // FSR = ±1.024 V
        static constexpr unsigned int CFG_PGA_0_512{0b100UL << CFG_PGA_POS}; // FSR = ±0.512 V
        static constexpr unsigned int CFG_PGA_0_256{0b101UL << CFG_PGA_POS}; // FSR = ±0.256 V

        static constexpr unsigned int CFG_MODE_CC{0b0UL << 8}; // Continuous-conversion mode
        static constexpr unsigned int CFG_MODE_SS{0b1UL << 8}; // Single-shot mode or power-down state (default)

        static constexpr unsigned int CFG_DR_8{0b000UL << 5}; // 8 SPS
        static constexpr unsigned int CFG_DR_16{0b001UL << 5}; // 16 SPS
        static constexpr unsigned int CFG_DR_32{0b010UL << 5}; // 32 SPS
        static constexpr unsigned int CFG_DR_64{0b011UL << 5}; // 64 SPS
        static constexpr unsigned int CFG_DR_128{0b100UL << 5}; // 128 SPS (default)
        static constexpr unsigned int CFG_DR_250{0b101UL << 5}; // 250 SPS
        static constexpr unsigned int CFG_DR_475{0b110UL << 5}; // 475 SPS
        static constexpr unsigned int CFG_DR_860{0b111UL << 5}; // 860 SPS

        static constexpr unsigned int CFG_COMP_MODE_TRADITIONAL{0b0UL << 4}; // Traditional comparator (default)
        static constexpr unsigned int CFG_COMP_MODE_WINDOW{0b1UL << 4}; // Window comparator

        static constexpr unsigned int CFG_COMP_POL_LOW{0b0UL << 3}; // Active low (default)
        static constexpr unsigned int CFG_COMP_POL_HIGH{0b1UL << 3}; // Active high

        static constexpr unsigned int CFG_COMP_LAT_DISABLE{0b0UL << 2}; // Nonlatching comparator (default)
        static constexpr unsigned int CFG_COMP_LAT_ENABLE{0b1UL << 2}; // Latching comparator

        static constexpr unsigned int CFG_COMP_QUE_ONE{0b00UL}; // Assert after one conversion
        static constexpr unsigned int CFG_COMP_QUE_TWO{0b01UL}; // Assert after two conversions
        static constexpr unsigned int CFG_COMP_QUE_FOUR{0b10UL}; // Assert after four conversions
        static constexpr unsigned int CFG_COMP_QUE_DISABLE{0b11UL}; // Disable comparator (default)

        // -----------------
        //  Read registers
        // -----------------

        std::unique_ptr<I2C_Slot> m_device;
        short int m_channel;

        // -----------------
        //  Calculation
        // -----------------

        static const float FSR[6]; // Full-scale range

        static constexpr float MIN_CODE{1 << 15}; // Resolution (16 bits)
        float m_abs_fsr = 2.048; // Absolute full-scale range
        float m_max_voltage = 3.3;

        [[nodiscard]] bool configure(int cfg);

        [[nodiscard]] float toVoltage(int value) const;

        [[nodiscard]] float normalize(float value) const;
    };
}
