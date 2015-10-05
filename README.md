package
==============================

Source file collector for vendor package

[![Latest Stable Version](https://poser.pugx.org/holyshared/package/v/stable)](https://packagist.org/packages/holyshared/package)
[![Build Status](https://travis-ci.org/holyshared/package.svg?branch=master)](https://travis-ci.org/holyshared/package)
[![Dependency Status](https://www.versioneye.com/user/projects/5610e428a193340015000009/badge.svg?style=flat)](https://www.versioneye.com/user/projects/5610e428a193340015000009)
[![License](https://poser.pugx.org/holyshared/package/license)](https://packagist.org/packages/holyshared/package)

Basic usage
------------------------------

Find the source from the package.

```hack
use package\PackageSpecification;

$package = new PackageSpecification(shape(
    'namespace' => 'package\\spec\\fixtures\\',
    'packageDirectory' => __DIR__ . '/fixtures'
));

$files = $package->getSourceFiles();

foreach ($files->items() as $file) {
    var_dump($file); // /path/to/example.hh
}
```

Instantiation
------------------------------

Get an instance from the source

```hack
use package\PackageSpecification;

$params = shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
);
$package = new PackageSpecification($params);

foreach ($package->getSourceFiles() as $source) {
    $instance = $package->resolve($source);  // return instance
    var_dump($instance);
}
```

Run the test
------------------------------

	composer install
	composer test
