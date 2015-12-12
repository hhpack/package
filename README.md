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
use hhpack\package;

$sources = package\package(shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
))->sources()->toImmVector();

foreach ($sources->items() as $source) {
	var_dump($source->getName()); // /path/to/example.hh
	var_dump($source->getDirectory()); // /path/to
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
use hhpack\package;
use hhpack\package\selector;

$package = package\package(shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
));

$interfaces = $package->classes(selector\interfaces())->toImmVector();

foreach ($interfaces as $interface) {
    var_dump($interface->getName()); // interface
}

$traits = $package->classes(selector\traits())->toImmVector();

foreach ($traits as $trait) {
    var_dump($trait->getName()); // trait
}
```

Instantiation of class
------------------------------

Get an instance from the source files

```hack
use hhpack\package;

$classes = package\package(shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
))->classes()->toImmVector();

foreach ($classes as $class) {
    $instance = $class->instantiate();
    var_dump($instance);
}
```

Pipeline of stream
------------------------------

You can build a pipeline.  
You can achieve when implement the interface **Middleware** and **StreamWrapper**.  

Please look at the **example/pipeline.hh** for details.

```hack
use hhpack\package;
use hhpack\package\examples\classes\FileStatTransformer;
use hhpack\package\examples\classes\FileStatOutput;

$pkg = package\package(shape(
    'namespace' => 'hhpack\\package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
));

$pkg->sources()
	->pipeTo(new FileStatTransformer())
	->pipeTo(new FileStatOutput());
```

Run the test
------------------------------

	composer install
	composer test
