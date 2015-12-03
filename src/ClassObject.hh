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

use Exception;
use ReflectionClass;
use ReflectionException;

final class ClassObject
{

    private ReflectionClass $class;

    public function __construct(
        private SourceFile $file,
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
        return $this->file->getName();
    }

    /**
     * Get package directory path
     */
    public function getPackageDirectory() : DirectoryPath
    {
        return $this->packageDirectory;
    }

    <<__Memoize>>
    public function getName() : string
    {
        return preg_replace('/^(\w+\\\\)+/', '', $this->getFullName());
    }

    /**
     * Get class full name
     */
    <<__Memoize>>
    public function getFullName() : string
    {
        $relativeClassName = $this->relativeClassNameFrom($this->getFileName());
        $fullClassName = $this->getNamespace() . '\\' . $relativeClassName;

        return $fullClassName;
    }

    /**
     * Get class full name
     */
    /*<<__Memoize>>
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
*/
    /**
     * Get new instance
     */
    public function instantiate<T>(array<mixed> $parameters = []) : T
    {
        try {
            $instance = $this->class->newInstanceArgs($parameters);
        } catch (Exception $exception) {
            throw new InstantiationException($this->getFullName());
        }

        return $instance;
    }

    private function initialize() : void
    {
        try {
            $this->class = new ReflectionClass($this->getFullName());
        } catch (ReflectionException $exception) {
            throw new UnknownClassException($this->getFullName());
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

    public function isAbstract() : bool
    {
        return $this->class->isAbstract();
    }

    public function isTrait() : bool
    {
        return $this->class->isTrait();
    }

    public function isInterface() : bool
    {
        return $this->class->isInterface();
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
