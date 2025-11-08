# Synapses

Synapses is a project that I came up with cause apple's enginuity is one of if not the best I came accross, and their userbase is the evidence.

I want to make a usable version of most of their features for other OSes, cause they will be beneficial if most users had it.

I started this journey cause my grade was going down in University and I panicked and started creating the best **Final Year Project** that anyone has ever scene.

The name synapses came to me one night, when I was reading and being philosophical... that's full of crap I laughed just writing that, as everyone knows in these days all products name is come up with AI so is this one, look for names of `nexus` that indicates the name was AI wink wink

The following are the features that I reaserched (`cough cough`... that ChatGPT gave me)

| **Category**                      | **Feature**                                  | **Description / Purpose**                                                                |
| --------------------------------- | -------------------------------------------- | ---------------------------------------------------------------------------------------- |
| **Continuity & Ecosystem**        | Handoff                                      | Start something on one device and continue it on another (e.g., Safari tab, Mail draft). |
|                                   | Universal Clipboard                          | Copy text/images/files on one device, paste on another instantly.                        |
|                                   | AirDrop                                      | Peer-to-peer encrypted file transfer between Apple devices.                              |
|                                   | Continuity Camera                            | Use iPhone as a Mac webcam or scan documents directly into Mac apps.                     |
|                                   | Universal Control                            | Single keyboard/mouse control across multiple Macs and iPads seamlessly.                 |
|                                   | Sidecar                                      | Extend or mirror Mac display on an iPad with Apple Pencil support.                       |
|                                   | Instant Hotspot                              | Mac/iPad can auto-connect to iPhone’s hotspot without entering a password.               |
| **Cloud Integration**             | iCloud Drive                                 | File syncing and versioning across all devices.                                          |
|                                   | iCloud Keychain                              | Passwords, 2FA codes, Wi-Fi credentials synced securely.                                 |
|                                   | iCloud Photos                                | Cloud photo library with automatic syncing and machine learning categorization.          |
|                                   | iMessage in iCloud                           | Messages synced across all devices, including edits and deletions.                       |
| **Privacy & Security**            | App Tracking Transparency                    | Lets users block apps from tracking across other apps/websites.                          |
|                                   | Mail Privacy Protection                      | Hides IP and prevents email tracking pixels.                                             |
|                                   | Private Relay                                | Apple’s encrypted relay for browsing privacy (partial VPN-like feature).                 |
|                                   | On-device ML                                 | Processing like Face ID, Siri suggestions, and photo recognition done locally.           |
| **AI & ML**                       | Siri                                         | Voice assistant tied into Apple ecosystem.                                               |
|                                   | Live Text                                    | Recognizes text in images and allows direct interaction (copy, translate, call).         |
|                                   | Visual Lookup                                | Identifies objects, plants, animals, landmarks in photos.                                |
|                                   | Personal Voice                               | Generates a digital voice clone for accessibility.                                       |
|                                   | Predictive Keyboard                          | Context-aware text prediction and autocorrect.                                           |
| **Productivity**                  | Spotlight                                    | Unified search across files, apps, web, and on-device data.                              |
|                                   | Shortcuts                                    | Visual automation tool for system-level scripting and workflows.                         |
|                                   | Focus Modes                                  | Custom notification and app filter profiles for different contexts.                      |
|                                   | Stage Manager                                | Window organization and multitasking system on macOS/iPadOS.                             |
|                                   | Quick Notes                                  | System-wide instant notes tied to context (app, webpage, etc.).                          |
|                                   | Universal Search APIs                        | Deep app integration with Spotlight and Siri suggestions.                                |
| **Media & Creativity**            | AirPlay                                      | Wireless streaming of audio/video across devices.                                        |
|                                   | Freeform                                     | Collaborative infinite canvas app.                                                       |
|                                   | GarageBand, iMovie, Final Cut Pro, Logic Pro | Native creative suite optimized for macOS/iOS.                                           |
|                                   | Photos Memories                              | ML-generated story compilations and albums.                                              |
| **System & Integration**          | Time Machine                                 | Incremental system-wide backups.                                                         |
|                                   | Apple File System (APFS)                     | High-performance, snapshot-based file system with encryption.                            |
|                                   | macOS Virtualization Framework               | Native hypervisor for running VMs (used in Apple Silicon).                               |
|                                   | SwiftUI                                      | Unified UI framework for all Apple platforms.                                            |
|                                   | Metal                                        | Low-overhead graphics and compute API.                                                   |
|                                   | Core ML                                      | On-device machine learning framework.                                                    |
|                                   | HealthKit / HomeKit / CarPlay                | APIs for health, home automation, and car integration.                                   |
| **Communication & Collaboration** | FaceTime                                     | Native video/audio calling with SharePlay for synced media.                              |
|                                   | SharePlay                                    | Shared media experiences in FaceTime and Messages.                                       |
|                                   | iMessage                                     | Encrypted messaging platform with stickers, games, and effects.                          |
|                                   | Mail, Calendar, Reminders, Notes             | Deep system integration and sync across devices.                                         |


As you can see there a ton of feature, but all rely on one thing one device connecting to the other seamlessly, that the first feature that I will be documenting or will try to.

---

## Feature One: Seamless Connection

Apple uses BLE (**Bluetooth Low Energy**), used for low energy output but great discovery for things like Airdrop

Apple's Secret Sauce is `AWDL`, yeah and it is not gaming that is `WASD`, which stands for `Apple's WiFi Direct Link` which in android space is `Wi-Fi Direct`

When they do handoff they do both bluetooth and wifi for data transfer. Like Handoffs, Clipboard Share, etc.

Bonjour (Zeroconf) is a unique of sending your device on a separate ip to make it only connect with devices of your devices ip type.

Current phase I only care about bare minimums, so for the database I will be using mongodb and for the code python.

### Database Schema

- users — main Apple-ID-like profile (email, name, prefs, encrypted secrets).

- devices — per-device records (keys, metadata, last seen).


---

**Users**
```json
{
  "id": "uuidv4",
  "username": "nahom",
  "email": "nahom@example.com",
  "email_verified": true,               // you said all verified
  "password_hash": "$argon2id$...",     // REQUIRED: no plaintext
  "kdf_params": { "type":"argon2id", "m":65536, "t":3, "p":1 },
  "key_bundle_encrypted": "v1:BASE64BLOB", // TOTP, recovery, seeds
  "created_at": "2025-11-08T18:00:00Z",
  "last_login": "2025-11-08T18:22:00Z",
  "failed_login_count": 0,
  "locked_until": null,
  "account_status": "active"
}

```

**Devices**
```json
{
  "id": "uuidv4",
  "user_id": "uuidv4",
  "name": "nahom.Fedora.Laptop",
  "os": "Fedora 43 (Linux)",
  "device_pubkey": "ed25519:BASE64",
  "registered_at": "2025-11-08T18:05:00Z",
  "last_seen": "2025-11-08T18:22:00Z",
  "flags": {}
}
```