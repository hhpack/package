package
==============================

[![Build Status](https://travis-ci.org/holyshared/package.svg?branch=master)](https://travis-ci.org/holyshared/package)


Basic usage
------------------------------

```hack
<?hh

use package\PackageFileCollector;

$collector = new PackageFileCollector();
$files = $collector->collectFrom('/path/to/src');

foreach ($files->items() as $file) {
    var_dump($file); // /path/to/example.hh
}
```

Run the test
------------------------------

	composer install
	composer test
