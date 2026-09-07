# Zellno Death Grave

Creates a persistent equipment grave when a player dies.

## Features

- Automatic grave creation at the death position.
- Equipped clothing and backpacks are transferred to the grave.
- Contents remain inside their original clothing and backpacks.
- The item held in the player's hands remains at the death location.
- Manual equipment recovery through the inventory interface.
- Grave automatically disappears when emptied.
- Remaining grave and equipment expire after 24 hours.
- Uses a vanilla DayZ cemetery tombstone model.
- No configuration file required.
- No CF, Dabs Framework or RaG dependency.

## Version

Current version: `0.0.13`

Tested on DayZ 1.29 with a dedicated server and a clean persistence restart.

## Installation

1. Subscribe to the mod.
2. Install it on the server.
3. Copy the public key to the server `keys` directory.
4. Load the mod on the server and all clients.
5. Restart the server.

## Important testing status

Automatic creation, equipment transfer, nested inventory persistence, manual
recovery and empty-grave deletion have passed local testing.

A dedicated two-player test confirming non-owner access restrictions is still
pending.

## Source code

https://github.com/Zellno/ZellnoDeathGrave

## License

MIT License.

## Monetization

Use on monetized DayZ servers is permitted only when the server is registered
and approved under Bohemia Interactive's server monetization program and
complies with its rules.
