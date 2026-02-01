import tkinter as tk
from tkinter import ttk, messagebox
import serial
import serial.tools.list_ports

# === Serial Setup ===
def get_arduino_port():
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        if 'Arduino' in p.description or 'CH340' in p.description:
            return p.device
    return None

try:
    port = get_arduino_port() or 'COM3'  # Fallback if auto-detect fails
    arduino = serial.Serial(port, 9600, timeout=1)
    print(f"Connected to Arduino on {port}")
except Exception as e:
    arduino = None
    print(f"Connection Error: {e}")
    messagebox.showerror("Connection Error", f"Could not connect to Arduino on {port}.\n{e}")

# === GUI Functions ===
def send_command(cmd):
    if arduino and arduino.is_open:
        try:
            arduino.write((cmd + '\n').encode())
            status_label.config(text=f"Sent: {cmd}")
            print(f"Command sent: {cmd}")
        except Exception as e:
            status_label.config(text="Error sending command.")
            print(f"Error: {e}")
    else:
        status_label.config(text="Arduino not connected.")
        print("Arduino not connected.")

def set_rpm():
    rpm = rpm_entry.get()
    if rpm.isdigit():
        rpm_int = int(rpm)
        send_command(f"RPM {rpm}")
        rpm_meter['value'] = rpm_int
        rpm_value_label.config(text=f"{rpm_int} RPM")
    else:
        messagebox.showwarning("Invalid Input", "Please enter a valid number.")

def set_direction():
    dir_choice = direction_var.get()
    send_command(dir_choice)

def start_motor():
    set_direction()
    send_command("START")

def stop_motor():
    send_command("STOP")
    rpm_meter['value'] = 0
    rpm_value_label.config(text="0 RPM")

# === GUI Setup ===
root = tk.Tk()
root.title("🌀 Centrifugal Feeder - Phoenix Industries")
root.geometry("700x600")
root.configure(bg="#1e1e2f")

# Fonts
HEADER_FONT = ("Segoe UI", 22, "bold")
LABEL_FONT = ("Segoe UI", 14)
BUTTON_FONT = ("Segoe UI", 13)

# Title
title_label = tk.Label(root, text="Phoenix Industries 🔸", font=HEADER_FONT, bg="#1e1e2f", fg="#ff9f43")
title_label.pack(pady=15)

sub_label = tk.Label(root, text="Bottle Unscrambler - Centrifugal Feeder Control Interface", font=("Segoe UI", 16), bg="#1e1e2f", fg="#48dbfb")
sub_label.pack()

# RPM Entry
rpm_frame = tk.Frame(root, bg="#1e1e2f")
tk.Label(rpm_frame, text="🎯 Set RPM:", font=LABEL_FONT, bg="#1e1e2f", fg="white").pack(side="left", padx=10)

rpm_entry = tk.Entry(rpm_frame, font=LABEL_FONT, width=10, bg="#2f3640", fg="white", relief="flat", insertbackground="white")
rpm_entry.insert(0, "25")
rpm_entry.pack(side="left", padx=10)

tk.Button(rpm_frame, text="⚙️ Apply", font=BUTTON_FONT, bg="#ff9f43", fg="white", command=set_rpm, relief="flat", padx=10).pack(side="left", padx=10)
rpm_frame.pack(pady=20)

# RPM Meter
tk.Label(root, text="📊 RPM Meter", font=LABEL_FONT, bg="#1e1e2f", fg="#ff9f43").pack()
rpm_meter = ttk.Progressbar(root, length=400, maximum=100, mode='determinate', style="TProgressbar")
rpm_meter.pack(pady=10)
rpm_value_label = tk.Label(root, text="0 RPM", font=("Segoe UI", 16), bg="#1e1e2f", fg="white")
rpm_value_label.pack()

# Direction Control
tk.Label(root, text="🔁 Select Direction", font=LABEL_FONT, bg="#1e1e2f", fg="#48dbfb").pack(pady=10)
direction_var = tk.StringVar(value="")

dir_frame = tk.Frame(root, bg="#1e1e2f")
tk.Radiobutton(dir_frame, text="↪️ Clockwise", variable=direction_var, value="CW", font=LABEL_FONT, bg="#1e1e2f", fg="white", selectcolor="#ff9f43", command=set_direction).pack(side="left", padx=20)
tk.Radiobutton(dir_frame, text="↩️ Counter-Clockwise", variable=direction_var, value="CCW", font=LABEL_FONT, bg="#1e1e2f", fg="white", selectcolor="#10ac84", command=set_direction).pack(side="left", padx=20)
dir_frame.pack(pady=10)

# Control Buttons
btn_frame = tk.Frame(root, bg="#1e1e2f")
tk.Button(btn_frame, text="▶️ Start Motor", font=BUTTON_FONT, bg="#10ac84", fg="white", command=start_motor, relief="flat", width=20, height=2).pack(side="left", padx=15, pady=10)
tk.Button(btn_frame, text="⛔ Stop Motor", font=BUTTON_FONT, bg="#ee5253", fg="white", command=stop_motor, relief="flat", width=20, height=2).pack(side="left", padx=15, pady=10)
btn_frame.pack(pady=20)

# Status & Footer
status_label = tk.Label(root, text="Status: Ready", font=LABEL_FONT, bg="#1e1e2f", fg="#48dbfb")
status_label.pack(pady=10)
footer_label = tk.Label(root, text="© 2025 Phoenix Industries | Developed by Dunith", font=("Segoe UI", 10), bg="#1e1e2f", fg="#576574")
footer_label.pack(side="bottom", pady=10)

# Style config
style = ttk.Style()
style.theme_use('default')
style.configure("TProgressbar", thickness=25, troughcolor="#2f3640", background="#ff9f43")

# Run the GUI loop
root.mainloop()
