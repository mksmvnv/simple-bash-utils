<h1>Simple Bash Utils</h1>

<p>This is an implementation of fake Unix commands cat and grep with tests for output data identity.</p>
<img src="./assets/linux.gif" alt="simple-bash-utils">

<h2>Description</h2>

<p>In this project, two Unix commands, Cat and Grep, were implemented. Afterwards, they were tested for identity with the original commands using tests written in Python. The commands themselves were written in the C language. This project was carried out during the main training at School 21 by Sber.</p>

<h2>How to Run</h2>

<ol>
    <li>Clone this repository to your local machine.</li>
    <li>Navigate to the project directory.</li>
    <li>Run the makefile from the cat or grep directory depending on which command you want to compile first:</li>
</ol>

<pre>
make all
make fake_cat/fake_grep
make test
make leak
make style
</pre>

<p>If you want to test the code with a fake tester, download Docker and run run.sh from materials/build.</p>

<pre>
./run.sh
</pre>

<p>After compiling with the makefile, you can run the executable file to independently test the functionality of the command.</p>

<pre>
./fake_cat
./fake_grep
</pre>

<p>You can also use the makefile to clean up the compiled data.</p>

<pre>
make clean
</pre>

<h2>License</h2>

<p>The project is licensed under the <a href="https://opensource.org/licenses/MIT">MIT License</a>.</p>
