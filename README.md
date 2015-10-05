package
==============================

Source file collector for vendor package

[![Latest Stable Version](https://poser.pugx.org/holyshared/package/v/stable)](https://packagist.org/packages/holyshared/package)
[![Build Status](https://travis-ci.org/holyshared/package.svg?branch=master)](https://travis-ci.org/holyshared/package)
[![Dependency Status](https://www.versioneye.com/user/projects/5610e428a193340015000009/badge.svg?style=flat)](https://www.versioneye.com/user/projects/5610e428a193340015000009)
[![License](https://poser.pugx.org/holyshared/package/license)](https://packagist.org/packages/holyshared/package)

Basic usage
------------------------------

```hack
<?hh

use package\FileCollector;

$collector = new FileCollector();
$files = $collector->collectFrom('/path/to/src');

foreach ($files->items() as $file) {
    var_dump($file); // /path/to/example.hh
}
```

Run the test
------------------------------

	composer install
	composer test
