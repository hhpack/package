<?hh //strict

/**
 * This file is part of package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace package;

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

    public function getClassFiles() : ClassFileStream
    {
        $collector = new FileCollector();
        $sourceFiles = $collector->collectFrom($this->getPackageDirectory());

        foreach ($sourceFiles->items() as $sourceFile) {
            yield new ClassFile(
                $sourceFile,
                $this->getNamespace(),
                $this->getPackageDirectory()
            );
        }
    }

}
