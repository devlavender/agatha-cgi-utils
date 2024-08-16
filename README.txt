agatha-cgi-utils

1. DESCRIPTION

Collection of CGI useful small tools, scripts, examples, etc by Ágatha Isabelle
Chris Moreira Guedes.

2. INSTRUCTIONS

To build type:
$ make

To install, run with proper permissions:
# make install

Create the dumper temporary dir and set permissions:
# mkdir -p /srv/cgi/agatha-cgi-utils/data/tmp/dumper/
# chmod -R 777 /srv/cgi/agatha-cgi-utils/data/tmp

Setup your web server to run the `/srv/cgi/agatha-cgi-utils/bin/dumper.cgi`
binary with the CGI handler, then configure it so that all desired requests are
processed by the script.

The script will output a `text/plain` response containing the UUID of the
request. You'll see a file with the UUID as the name and the `.dump` extension
in the `/srv/cgi/agatha-cgi-utils/data/tmp/dumper/` directory containing all
the request available data.

You can specify alternative directories by passing the `PREFIX`, `PKGDIR`,
`CFGDIR`, `DATADIR` and `TMPDIR` environment variabkes to the command `make`
and adjusting the following steps accordingly.`

3. DEBUGING

To build the project with debug symbols, pass the `DEBUG` environment variable
set to a value between 1 and 3. This is the debug level passed to the C
compiler using the `-g` flag (i.e. DEBUG=3 implies `-g3`).

4. LICENSE
Unless otherwise specified, all files are licensed under the AGPL v3. See
`LICENSE.txt` for the license text.
