# Cooking recipe, checkout Cook at https://github.com/serweryn617/cook

from cook.build import BuildStep, LocalBuildServer


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
            BuildStep(command='mkdir -p build'),
            BuildStep(workdir='build', command='mkdir -p generated/pio'),

            BuildStep(workdir='build', command='cmake ../firmware -DSIDE=0'),
            BuildStep(workdir='build', command='cmake --build . -j'),
            BuildStep(command='cp build/keypad.uf2 keypad_left.uf2'),

            BuildStep(workdir='build', command='cmake ../firmware -DSIDE=1'),
            BuildStep(workdir='build', command='cmake --build . -j'),
            BuildStep(command='cp build/keypad.uf2 keypad_right.uf2'),
        ],
    },

    'copy_compile_commands': {
        'build_servers': [
            LocalBuildServer(),
        ],

        'build_steps': [
            BuildStep(command='cp build/compile_commands.json .vscode/compile_commands.json'),
        ],
    }
}