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

    private ReflectionClass $class;

    public function __construct(
        private SourceFileName $name,
        private PackageNamespace $namespace,
        private DirectoryPath $packageDirectory
    )
    {
        $this->class = new ReflectionClass(UnknownClassType::class);
        $this->initialize();
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
    <<__Memoize>>
    public function getClassName() : string
    {
        $relativeClassName = $this->relativeClassNameFrom($this->getFileName());
        $fullClassName = $this->getNamespace() . '\\' . $relativeClassName;

        return $fullClassName;
    }

    <<__Memoize>>
    public function getShortClassName() : string
    {
        return preg_replace('/^(\w+\\\\)+/', '', $this->getClassName());
    }

    /**
     * Get new instance
     */
    public function instantiate<T>(array<mixed> $parameters = []) : T
    {
        try {
            $instance = $this->class->newInstanceArgs($parameters);
        } catch (Exception $exception) {
            throw new InstantiationException($this->getClassName());
        }

        return $instance;
    }

    private function initialize() : void
    {
        try {
            $this->class = new ReflectionClass($this->getClassName());
        } catch (ReflectionException $exception) {
            throw new UnknownClassException($this->getClassName());
        }
    }

    public function implementsInterface(string $interfaceName) : bool
    {
        try {
            $result = $this->class->implementsInterface($interfaceName);
        } catch (ReflectionException $exception) {
            $result = false;
        }

        return $result;
    }

    public function isSubclassOf(string $className) : bool
    {
        return $this->class->isSubclassOf($className);
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
