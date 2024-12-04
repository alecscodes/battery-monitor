# 🔋 Battery Monitor

A macOS utility that helps extend your laptop's battery lifespan by maintaining optimal charge levels between 40% and 60%.

## 🤔 Why You Need This

Keeping your MacBook's battery between 40% and 60% charge can significantly extend its lifespan. This app helps you maintain these optimal levels by:

- Warning you when battery drops below 40% (time to charge)
- Alerting you when charge exceeds 60% (time to unplug)

## ✨ Features

- 🔋 Real-time battery level monitoring
- 🔔 Automatic notifications at optimal charging points
- 🚀 Launches automatically at startup
- 💡 Lightweight with minimal CPU usage
- 🔄 Continuous background operation

## 💻 System Requirements

- 🍎 macOS 10.12 (Sierra) or later
- 💾 10MB free disk space
- 🌐 Internet connection (for installation only)
- 🛠️ make utility
- ⚡ Xcode Command Line Tools

## 📥 Installation Guide

### 🔧 Step 1: Install Required Tools

1. First, check if make is installed:

   ```bash
   which make
   ```

   If not found, install it using Homebrew:

   ```bash
   brew install make
   ```

   If you don't have Homebrew, install it first:

   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. Check if Xcode Command Line Tools are installed:

   ```bash
   xcode-select -p
   ```

   If you see an error, install them:

   ```bash
   xcode-select --install
   ```

   Click "Install" when prompted and wait for completion.

### 🚀 Step 2: Download and Install Battery Monitor

1. Download the latest release:

   ```bash
   git clone https://github.com/alecscodes/battery-monitor.git
   cd battery-monitor
   ```

2. Run the installation script:

   ```bash
   ./scripts/setup.sh
   ```

That's it! The app is now running and will start automatically when you log in.

## ⚙️ How It Works

The app runs silently in the background and checks your battery level every 5 minutes. You'll receive notifications only when:

- Battery drops below 40% while not charging
- Battery exceeds 60% while charging

## 🔍 Troubleshooting

1. If notifications don't appear:

   - Go to System Preferences > Notifications
   - Ensure `Script Editor` is allowed to send notifications

2. If the app doesn't start:
   - Open Terminal
   - Run: `launchctl load ~/Library/LaunchAgents/com.alecscodes.battery_monitor.plist`

## 🗑️ Uninstall

To remove Battery Monitor:

1. Open Terminal
2. Navigate to the battery-monitor directory
3. Run the uninstall script:

   ```bash
   ./scripts/uninstall.sh
   ```

4. Delete the battery-monitor folder

## 💬 Support

Found a bug? Have a suggestion? Please open an issue on our GitHub repository.

## ⚖️ License

MIT License - Feel free to use, modify, and distribute this software.
