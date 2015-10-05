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

final class PackageSpecification
{

    private PackageNamespace $namespace;
    private DirectoryPath $packageDirectory;

    public function __construct(
        Package $package
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

    public function getSourceFiles() : SourceFileVector
    {
        $collector = new FileCollector();
        return $collector->collectFrom($this->getPackageDirectory());
    }

    public function resolve<T>(SourceFile $file) : T
    {
        $reflection = $this->reflectionFrom($file);
        return $reflection->newInstance();
    }

    public function resolveWith<T>(SourceFile $file, array<mixed> $parameters) : T
    {
        $reflection = $this->reflectionFrom($file);
        return $reflection->newInstanceArgs($parameters);
    }

    private function reflectionFrom<T>(SourceFile $file) : ReflectionClass
    {
        $relativeClass = $this->relativeClassFrom($file);
        $fullClassName = $this->namespace . $relativeClass;

        try {
            $reflection = new ReflectionClass($fullClassName);
        } catch (ReflectionException $exception) {
            throw new NotPackageFileException();
        }

        return $reflection;
    }

    private function relativeClassFrom(SourceFile $file) : string
    {
        $replaceTargets = [
            $this->packageDirectory . '/',
            '/',
            '.hh'
        ];
        $replaceValues = [
            '',
            '\\',
            ''
        ];
        $relativeClass = str_replace($replaceTargets, $replaceValues, $file);

        return $relativeClass;
    }

}
