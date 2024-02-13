#!python3

from itertools import combinations_with_replacement
from random import randint
from os import system

fake = './fake_cat'
original = 'cat'

file_name = 'test_'
file_format = '.testing'

test_files = [
    'tests/text_file_1',
    'tests/text_file_2',
    'tests/text_file_3'
]

flags = {
    '-b',
    '-e',
    '-n',
    '-s',
    '-v',
    '-t'
}

all_var = list(combinations_with_replacement(flags, len(flags)))

def file_comparison(a, b):
    try:
        with open(a) as file_1:
            with open(b) as file_2:
                a, b = file_1.read(), file_2.read()
                if a == b:
                    print('\033[42m\033[1m YES \033[0m')
                else:
                    print('\033[41m\033[1m NO \033[0m')
    except FileNotFoundError:
        print('One or both files not found.')


for test in range(len(all_var)):
    current_flags_ = all_var[test]
    for current_flags in (current_flags_, set(current_flags_)):
        random_test_file = test_files[randint(0, 2)]
        print(f'Test [{test + 1} / {len(all_var)}] - ', end='')
        for i, command in (('fake', fake), ('original', original)):
            command_execution = f'{command} {" ".join(current_flags)} {random_test_file} > {file_name + i + file_format}'
            system('echo "{}" >> commands.testing'.format(command_execution));
            system(command_execution)
        file_comparison(file_name + 'fake' + file_format,
                        file_name + 'original' + file_format)

system('rm -rf *' + file_format)