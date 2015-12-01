<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\package;

use \ReflectionClass;
use \ReflectionException;

final class Package
{

    private PackageNamespace $namespace;
    private DirectoryPath $packageDirectory;

    public function __construct(
        PackageOptions $package
    )
    {
        $this->namespace = (string) $package['namespace'];
        $this->packageDirectory = realpath($package['packageDirectory']);
    }

    <<__Memoize>>
    public function getNamespace() : PackageNamespace
    {
        $atoms = explode('\\', $this->namespace);
        $atoms = (new Vector($atoms))->filter((string $atom) ==> {
            return trim($atom) !== '';
        });
        return implode('\\', $atoms);
    }

    public function getPackageDirectory() : DirectoryPath
    {
        return $this->packageDirectory;
    }

    public function sources(Matcher<SourceFile> $matcher = new AnyMatcher()) : SourceFileStreamWrapper
    {
        $collector = new FileCollector($this->getPackageDirectory());
        return $collector->collect($matcher);
    }

    public function classes(Matcher<ClassObject> $matcher = new AnyMatcher()) : ClassStreamWrapper
    {
        $middleware = ClassTransformer::fromOptions(shape(
            'namespace' => $this->getNamespace(),
            'packageDirectory' => $this->getPackageDirectory()
        ));
        return $this->sources()->pipe($middleware)->select($matcher);
    }

    public static function fromOptions(PackageOptions $package) : this
    {
        return new static($package);
    }

}
