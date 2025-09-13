# Akolyte

⌨️ Low profile mechanical split keyboard

---

![](/pictures/pic.jpg)

## Building firmware

Prerequisites:
 - `docker`

Firmware can be built using [cook-builder](https://github.com/serweryn617/cook):

**Setup:** initialize submodules and build Docker image. Has to be run only once:

```bash
cook setup
```

**Build:** build everything. Output files will be copied to the `output` directory:

```bash
cook
```

For complete list of commands run `cook -i`.
