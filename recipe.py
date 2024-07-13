# Cooking recipe, checkout Cook at https://github.com/serweryn617/cook

from cook.build import BuildStep, LocalBuildServer, RemoteBuildServer, Responder
from cook.cli import settings
from cook.sync import SyncDirectory, SyncExclude, SyncFile


default_build_server = 'local'
default_project = 'build_all'


build_servers = [
    'local',
]


projects = {
    'build_all': {
        'components': [
            'firmware',
            'copy_compile_commands',
        ],
    },

    'firmware': {
        'build_servers': [
            LocalBuildServer(),
        ],

        'build_steps': [
            BuildStep(workdir='firmware', command='mkdir -p build'),
            BuildStep(workdir='firmware', command='mkdir -p build/generated/pio'),

            BuildStep(workdir='firmware/build', command='cmake .. -DSIDE=0'),
            BuildStep(workdir='firmware/build', command='cmake --build . -j'),
            BuildStep(command='cp firmware/build/keypad.uf2 keypad_left.uf2'),

            BuildStep(workdir='firmware/build', command='cmake .. -DSIDE=1'),
            BuildStep(workdir='firmware/build', command='cmake --build . -j'),
            BuildStep(command='cp firmware/build/keypad.uf2 keypad_right.uf2'),
        ],
    },

    'copy_compile_commands': {
        'build_servers': [
            LocalBuildServer(),
        ],

        'build_steps': [
            BuildStep(command='cp firmware/build/compile_commands.json .vscode/compile_commands.json'),
        ],
    }
}