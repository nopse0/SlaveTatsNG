# Changes

## 0.8.0

* The boolean field ``gloss`` in tattoos isn't used anymore, it has been replaced by two new float fields, ``glossiness`` and ``specularstrength``.

* Three other new fields have been added to tattoos: ``specularstrength``, ``emissivemult`` and ``glowtexture``.

* Besides the old ``apply_overlay`` function in ``SlaveTats.psc``, a new function ``apply_overlay_ex`` has been added to ``SlaveTatsNG.psc``:

  ```
  bool function apply_overlay_ex(Actor target, bool isFemale, string area, int slot, string path, int color, int glow, float glossiness = 0.0, string bump_path = "", float alpha = 1.0, float specular = 0.0, string glow_path = "", float emissive_mult = 1.0) global native
  ```
  It contains the above mentioned ``gloss`` change and the three new fields for the NiOverride parameters ``SpecularStrength``, ``EmissiveMult`` and ``Texture[glow/detail]``.
  The old Papyrus function in ``SlaveTats.psc`` with boolean ``gloss`` parameter still exists; if ``gloss = true``, it calls ``apply_overlay_ex`` with hardcoded ``glossiness = 5.0`` and ``specularstrength = 5.0`` parameters.

  ```
  bool function apply_overlay(Actor target, bool isFemale, string area, int slot, string path, int color, int glow, bool gloss, string bump = "", float alpha = 1.0) global native
  ```
  Note: ``apply_overlay/apply_overlay_ex`` only apply NiOverride overlays, they don't change the SlaveTats JContainer tattoos, so they shouldn't be called directly. Instead edit the SlaveTats tattoos with JContainer or SlaveTats functions, and then call ``synchronize_tattoos``.

* The tattoo version (``.SlaveTats.version``) of actors is changed from ``1.0`` to ``2.0``.