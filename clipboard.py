import subprocess
import platform
import subprocess

def get_clipboard():
    system = platform.system()

    if system == "Windows":
        try:
            # Method 1: Using pyperclip (needs installation)
            import pyperclip
            return pyperclip.paste()
        except ImportError:
            # Method 2: Using PowerShell
            result = subprocess.run('powershell -Command "Get-Clipboard"', capture_output=True, text=True, shell=True)
            return result.stdout.strip()

    elif system == "Linux":
        try:
            # Try xclip first (most common)
            result = subprocess.run(['xclip', '-selection', 'clipboard', '-out'],
                                    capture_output=True, text=True)
            if result.returncode == 0:
                return result.stdout
        except FileNotFoundError:
            try:
                # Try xsel as fallback
                result = subprocess.run(['xsel', '--clipboard', '--output'],
                                        capture_output=True, text=True)
                return result.stdout
            except FileNotFoundError:
                return "Clipboard utilities not installed"

    else:
        return "Unsupported platform"


# Usage
clipboard_content = get_clipboard()
print(f"Clipboard content: {clipboard_content}")