# Cooking recipe, checkout Cook at https://github.com/serweryn617/cook

from cook.build import BuildStep, LocalBuildServer, local_build_from_list


default_build_server = 'local'
default_project = 'build_all'


build_servers = [
    'local',
]


projects = {}


projects['build_all'] = {
    'components': [
        'firmware',
        'copy_compile_commands',
    ],
}


projects['firmware'] = local_build_from_list([
    'mkdir -p build',
    ('build', 'mkdir -p generated/pio'),

    ('build', 'cmake ../firmware -DSIDE=0'),
    ('build', 'cmake --build . -j'),
    'cp build/keypad.uf2 keypad_left.uf2',

    ('build', 'cmake ../firmware -DSIDE=1'),
    ('build', 'cmake --build . -j'),
    'cp build/keypad.uf2 keypad_right.uf2',
])


projects['copy_compile_commands'] = local_build_from_list([
    'cp build/compile_commands.json .vscode/compile_commands.json'
])
