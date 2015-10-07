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

use Exception;
use ReflectionClass;
use ReflectionException;

final class ClassFile
{

    public function __construct(
        private SourceFileName $name,
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
    public function getFileName() : SourceFileName
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
        $fullClassName = $this->getNamespace() . '\\' . $relativeClassName;

        return $fullClassName;
    }

    /**
     * Get new instance
     */
    public function instantiate<T>(array<mixed> $parameters = []) : T
    {
        try {
            $instance = $this->reflect()->newInstanceArgs($parameters);
        } catch (Exception $exception) {
            throw new InstantiationException($this->getClassName());
        }

        return $instance;
    }

    <<__Memoize>>
    private function reflect() : ReflectionClass
    {
        try {
            $reflection = new ReflectionClass($this->getClassName());
        } catch (ReflectionException $exception) {
            throw new AutoloadException($this->getClassName());
        }

        return $reflection;
    }

    public function implementsInterface(string $interfaceName) : bool
    {
        return $this->reflect()->implementsInterface($interfaceName);
    }

    public function isSubclassOf(string $className) : bool
    {
        return $this->reflect()->isSubclassOf($className);
    }

    private function relativeClassNameFrom(SourceFileName $file) : string
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
