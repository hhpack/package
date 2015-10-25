package
==============================

Package utility library for vendor.  
Easily and quickly, and you can find a class or interface.

[![Latest Stable Version](https://poser.pugx.org/hhpack/package/v/stable)](https://packagist.org/packages/hhpack/package)
[![Build Status](https://travis-ci.org/hhpack/package.svg?branch=master)](https://travis-ci.org/hhpack/package)
[![Dependency Status](https://www.versioneye.com/user/projects/5610e428a193340015000009/badge.svg?style=flat)](https://www.versioneye.com/user/projects/5610e428a193340015000009)
[![License](https://poser.pugx.org/hhpack/package/license)](https://packagist.org/packages/hhpack/package)

Basic usage
------------------------------

Find the source file from the package.

```hack
use package\Package;

$sources = Package::fromOptions(shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
))->sources()->toImmVector();

foreach ($sources->items() as $source) {
	var_dump($source->getName()); // /path/to/example.hh
	var_dump($source->getDirectory()); // /path/to
}
```

Result of filtering
------------------------------

Use the filtering api, you can filter the results.  
Supported api is as follows.

* implementsInterface
* subclassOf
* classes
* abstractClasses
* traits
* interfaces
* startsWith
* endsWith
* select

In the following we are looking for a interface and traits.

```hack
use package\Package;

$package = Package::fromOptions(shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
));

$interfaces = $package->classes()
	->interfaces()
	->toImmVector();

foreach ($interfaces as $interface) {
    var_dump($interface->getName()); // interface
}

$traits = $package->classes()
	->traits()
	->toImmVector();

foreach ($traits as $trait) {
    var_dump($trait->getName()); // trait
}
```

Instantiation of class
------------------------------

Get an instance from the source files

```hack
use package\Package;

$classes = Package::fromOptions(shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
))->classes()->toImmVector();

foreach ($classes as $class) {
    $instance = $class->instantiate();
    var_dump($instance);
}
```

Run the test
------------------------------

	composer install
	composer test
