import subprocess

def release():
    print(f"Building environment: {"release"}")
    result = subprocess.run(["pio", "run", "-e", "release"])
    if result.returncode != 0:
        raise SystemExit("Failed to release")

release()