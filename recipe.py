# Cooking recipe, checkout Cook at https://github.com/serweryn617/cook

from cook.build import BuildStep, LocalBuildServer
import os
from pathlib import Path


def docker_command(command=None, interactive=False):
    # TODO: use shlex for quoting command
    return ' '.join(f'''
        docker run --rm
        {'-it' if interactive else ''}
        -u {os.getuid()}:{os.getgid()}
        -v {Path.cwd() / 'firmware'}:/workspace/firmware
        -v {Path.cwd() / 'sdk'}:/workspace/sdk
        -v {Path.cwd() / 'build'}:/workspace/build
        -e PICO_SDK_PATH=/workspace/sdk/pico-sdk
        -w /workspace
        pico_builder
        /bin/bash
        {'' if interactive else f'-c "{command}"'}
    '''.split())


default_build_server = 'local'
default_project = 'build'


build_servers = [
    'local',
]


projects = {}


projects['setup'] = {
    'components': [
        'init_submodules',
        'build_docker_image',
    ],
}


projects['build'] = {
    'components': [
        'build_firmware_docker',
        'copy_compile_commands',
    ],
}


projects['init_submodules'] = (
    ('sdk', 'git submodule update --init --depth 1 pico-sdk'),
    'git submodule status',

    ('sdk/pico-sdk/lib', 'git submodule update --init --depth 1 tinyusb'),
    'git submodule status',
)


projects['build_docker_image'] = [
    'docker build -t pico_builder .'
]


projects['build_firmware_docker'] = {
    'build_servers': [
        LocalBuildServer(),
    ],

    'build_steps': [
        'mkdir -p build/generated/pio',

        BuildStep(command=docker_command("cd /workspace/build && cmake ../firmware -DSIDE=left && cmake --build . -j")),
        BuildStep(command='cp build/akolyte/akolyte.uf2 akolyte_left.uf2'),

        BuildStep(command=docker_command("cd /workspace/build && cmake ../firmware -DSIDE=right && cmake --build . -j")),
        BuildStep(command='cp build/akolyte/akolyte.uf2 akolyte_right.uf2'),
    ],
}


projects['build_firmware'] = [
    BuildStep(command='mkdir -p build'),
    ('build', 'mkdir -p generated/pio'),

    ('build', 'cmake ../firmware -DSIDE=left'),
    ('build', 'cmake --build . -j'),
    'cp build/akolyte/akolyte.uf2 akolyte_left.uf2',

    ('build', 'cmake ../firmware -DSIDE=right'),
    ('build', 'cmake --build . -j'),
    'cp build/akolyte/akolyte.uf2 akolyte_right.uf2',
]


projects['copy_compile_commands'] = [
    'cp build/compile_commands.json .vscode/compile_commands.json',
    ('.vscode', f'sed -i "s#/workspace#{Path.cwd()}#g" compile_commands.json'),  # TODO: use build dir instead of vscode
]


projects['docker_interactive'] = [
    docker_command(interactive=True)
]
