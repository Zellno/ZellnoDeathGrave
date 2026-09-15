# Changelog

All notable changes to Zellno Death Grave are documented in this file.

## 0.0.14 - 2026-09-15

### Fixed

- Ruined clothing is no longer rejected when transferred into a Zellno Death
  Grave attachment slot.
- Nested items inside ruined clothing are preserved with their parent clothing.

### Scope

- The exception applies only when `Clothing` is attached to
  `ZellnoDeathGrave_Container`.
- Vanilla attachment rules remain unchanged for all other destinations.

### Validated

- Two ruined clothing items containing identifiable nested inventory were
  transferred successfully.
- Both ruined clothing items and their contents survived a clean server
  restart.
- Both ruined clothing items were recovered with their contents intact.
- The grave was deleted after its final stored equipment root was removed.
- No Death Grave error, invalid-location discard or persistence-corruption
  warning appeared in the test logs.

## 0.0.13 - 2026-09-06

### Added

- Narrowly scoped clothing inventory validation for equipment attached to a
  Zellno Death Grave.

### Fixed

- Nested items inside clothing and backpacks are no longer discarded as
  invalid locations when the Central Economy restores a grave after restart.
- Loaded equipment now retains its nested inventory across a clean server
  restart.

### Validated

- Successful dedicated-server compilation on DayZ 1.29.
- Automatic grave creation and owner assignment.
- Direct equipment-root transfer.
- Item-in-hands retention at the death location.
- Persistence of loaded clothing and backpacks after restart.
- Complete manual recovery of equipment and nested contents.
- Automatic deletion of the empty grave.
- No Death Grave compilation errors, invalid-location discards or persistence
  corruption warnings in the test logs.

### Multiplayer validation

- Confirmed on the hosted server that a non-owner cannot view or remove
  equipment from another player's grave.
- Confirmed that the owner retains normal recovery access.

## 0.0.12 - 2026-09-06

### Changed

- Added mannequin-oriented clothing configuration.

### Result

- Compiled and ran successfully, but did not prevent nested inventory from
  being discarded during persistence restoration.

## 0.0.11 - 2026-09-03

### Changed

- Added an empty, non-openable owned-cargo configuration.

### Result

- Compiled and ran successfully, but did not resolve nested clothing
  persistence.

## 0.0.10 - 2026-09-02

### Added

- Automatic grave creation.
- Direct equipment attachment transfer.
- Owner identity persistence and client visibility filtering.
- 24-hour lifetime.
- Automatic deletion after the final equipment root is removed.

### Changed

- Retired incompatible engine inventory and hand-event hooks.
