# zephyrApps repo
zephyrApps is a collection of demos, apps, etc. organized in different Git branchs.

# List of Branches
The list of branches in the repo include:
* main
  * this README
* SmartWatch
  * Wearable example application optimized for the i.MX RT500 MCU

# Getting started with a branch
Each branch has a README file with instructions for getting started.  To review, you can use a browser to view the [zephyrApps branches](https://github.com/nxp-zephyr/apps_zephyr/branches), and find the desired README.

# General folder structure:
Branches may differ, but in general this is the folder structure of the ZephyrApps folder after the `west init` command.
```
zephyrApps/
│
├── modules/                    # other modules pulled in by West
│   ├── hal/
│   │   └── nxp/
├── nxp/                        # West manifest repo, and applications
│   ├── apps/
└── zephyr/                     # module pulled in by West from zephyr-proper or NXP fork
```
