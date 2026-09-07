# Changelog

All notable changes to Zellno Death Grave are documented in this file.

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

### Pending

- Two-player validation of non-owner inventory visibility and access.

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
