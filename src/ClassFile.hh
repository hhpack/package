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

use ReflectionClass;
use ReflectionException;

final class ClassFile
{

    public function __construct(
        private SourceFile $name,
        private PackageNamespace $namespace,
        private DirectoryPath $packageDirectory
    )
    {
    }

    /**
     * Get namespace
     */
    public function getNamespace() : PackageNamespace
    {
        return $this->namespace;
    }

    /**
     * Get source file name
     */
    public function getFileName() : SourceFile
    {
        return $this->name;
    }

    /**
     * Get package directory path
     */
    public function getPackageDirectory() : DirectoryPath
    {
        return $this->packageDirectory;
    }

    /**
     * Get class full name
     */
    public function getClassName() : string
    {
        $relativeClassName = $this->relativeClassNameFrom($this->getFileName());
        $fullClassName = $this->getNamespace() . $relativeClassName;

        return $fullClassName;
    }

    /**
     * Get new instance
     */
    public function instantiate<T>(array<mixed> $parameters = []) : T
    {
        $className = $this->getClassName();

        try {
            $reflection = new ReflectionClass($className);
        } catch (ReflectionException $exception) {
            throw new NotPackageFileException("Could not instantiate the $className\nPlease be $className is sure possible autoload");
        }

        return $reflection->newInstanceArgs($parameters);
    }

    private function relativeClassNameFrom(SourceFile $file) : string
    {
        $replaceTargets = [
            $this->getPackageDirectory() . '/',
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
