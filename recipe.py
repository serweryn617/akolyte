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
        'compile_commands',
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
        BuildStep(command=docker_command("cd /workspace/build && cmake ../firmware -GNinja && ninja")),

        'mkdir -p output',
        BuildStep(command='cp build/akolyte/akolyte_left.uf2 output/akolyte_left.uf2'),
        BuildStep(command='cp build/akolyte/akolyte_right.uf2 output/akolyte_right.uf2'),
    ],
}


projects['compile_commands'] = [
    ('build', f'sed -i "s#/workspace#{Path.cwd()}#g" compile_commands.json'),
]


projects['docker_interactive'] = [
    docker_command(interactive=True)
]
