#!python3

from os import system
from random import randint

fake = './fake_grep'
original = 'grep'

file_name = 'test_'
file_format = ".testing"

template = '[0-9]'
test_files = [
    './tests/text_file_1',
    './tests/text_file_2',
    './tests/text_file_3'
]
test_template = './tests/test_template'
random_test_file = test_files[randint(0, 2)]

testing = [
    f'-e {template} -e {test_template} {random_test_file}',
    f'-f {test_template} -e {template} {random_test_file}',
    f'-f {test_template} fake_grep.c fake_grep.h',
    f'-vf {test_template} {random_test_file}',
    f'-cf {test_template} {random_test_file}',
    f'-lf {test_template} {random_test_file}',
    f'-nf {test_template} {random_test_file}',
    f'-hf {test_template} {random_test_file}',
    f'-h if {random_test_file} fake_grep.h',
    f'-ie {template} {random_test_file}',
    f'-ve {template} {random_test_file}',
    f'-ce {template} {random_test_file}',
    f'-le {template} {random_test_file}',
    f'-ne {template} {random_test_file}',
    f'-he {template} {random_test_file}',
    f'-se {template} {random_test_file}',
    f'-oe {template} {random_test_file}',
    f'-iv {template} {random_test_file}',
    f'-ic {template} {random_test_file}',
    f'-il {template} {random_test_file}',
    f'-in {template} {random_test_file}',
    f'-ih {template} {random_test_file}',
    f'-is {template} {random_test_file}',
    f'-io {template} {random_test_file}',
    f'-vc {template} {random_test_file}',
    f'-vl {template} {random_test_file}',
    f'-vn {template} {random_test_file}',
    f'-vh {template} {random_test_file}',
    f'-vs {template} {random_test_file}',
    f'-vo {template} {random_test_file}',
    f'-cl {template} {random_test_file}',
    f'-cn {template} {random_test_file}',
    f'-ch {template} {random_test_file}',
    f'-cs {template} {random_test_file}',
    f'-co {template} {random_test_file}',
    f'-ln {template} {random_test_file}',
    f'-lh {template} {random_test_file}',
    f'-ls {template} {random_test_file}',
    f'-lo {template} {random_test_file}',
    f'-nh {template} {random_test_file}',
    f'-ns {template} {random_test_file}',
    f'-no {template} {random_test_file}',
    f'-hs {template} {random_test_file}',
    f'-ho {template} {random_test_file}',
    f'-l {template} {random_test_file}',
    f'-v {template} {random_test_file}',
    f'-c {template} {random_test_file}',
    f'-n {template} {random_test_file}',
    f'-o {template} {random_test_file}',
    f'[0-9] {random_test_file}',
    f'-i RY {random_test_file}'
]


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

for index in range(len(testing)):
    print(f'Test [{index + 1} / {len(testing)}] grep {testing[index]} - ', end='')
    system(f'{fake} {testing[index]} > {file_name + "0" + file_format}')
    system(f'{original} {testing[index]} > {file_name + "1" + file_format}')
    file_comparison(file_name+'0'+file_format, file_name+'1'+file_format)

system('rm -rf *' + file_format)