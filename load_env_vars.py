from pathlib import Path

Import("env")

project_dir = Path(env["PROJECT_DIR"])
env_file = project_dir / ".env"

if not env_file.exists():
    print("No .env file found")
    Return()

for line in env_file.read_text().splitlines():
    line = line.strip()

    if not line or line.startswith("#"):
        continue

    key, value = map(str.strip, line.split("=", 1))

    env.Append(
        CPPDEFINES=[(key, value)]
    )

    print(f"Loaded env var: {key}={value}")
