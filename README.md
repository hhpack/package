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
use hhpack\package\VendorPackage;

$sources = VendorPackage::fromItems([
    Pair { 'package\\examples\\classes\\', realpath(__DIR__ . '/src') }
])->sources();

foreach ($sources as $source) {
	var_dump($source->name()); // /path/to/example.hh
	var_dump($source->directory()); // /path/to
}
```

Selection of elements
------------------------------

You can select the elements in the following function.

* hhpack\package\implementsInterface
* hhpack\package\subclassOf
* hhpack\package\classes
* hhpack\package\abstractClasses
* hhpack\package\traits
* hhpack\package\interfaces
* hhpack\package\instantiable
* hhpack\package\startsWith
* hhpack\package\endsWith

In the following we are looking for a interface and traits.

```hack
use hhpack\package as package;
use hhpack\package\VendorPackage;

$interfaces = VendorPackage::fromItems([
    Pair { 'package\\examples\\classes\\', realpath(__DIR__ . '/src') }
])->classes(package\interfaces());

foreach ($interfaces as $interface) {
    var_dump($interface->name()); // interface
}

$traits = VendorPackage::fromItems([
    Pair { 'package\\examples\\classes\\', realpath(__DIR__ . '/src') }
])->classes(package\traits());

foreach ($traits as $trait) {
    var_dump($trait->getName()); // trait
}
```

Instantiation of class
------------------------------

Get an instance from the source files

```hack
use hhpack\package\VendorPackage;

$instances = VendorPackage::fromItems([
    Pair { 'package\\examples\\classes\\', realpath(__DIR__ . '/src') }
])->classes()->map(($class) ==> $class->instantiate());

foreach ($instances as $instance) {
    var_dump($instance);
}
```

Pipeline of stream
------------------------------

You can build a pipeline.  
You can achieve when implement the interface **Middleware** and **Stream**.  

Please look at the **example/pipeline.hh** for details.

```hack
use hhpack\package\VendorPackage;
use hhpack\package\examples\classes\FileStatTransformer;
use hhpack\package\examples\classes\FileStatOutput;

$package = VendorPackage::fromItems([
    Pair { 'package\\examples\\classes\\', realpath(__DIR__ . '/src') }
]);

$package->sources()
    ->pipeTo(new FileStatTransformer())
    ->pipeTo(new FileStatOutput());
```

Run the test
------------------------------

	composer install
	composer test
