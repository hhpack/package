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

final class ClassObject implements NamedObject
{

    private ReflectionClass $class;

    public function __construct(
        private string $namespace,
        private string $packageDirectory,
        private SourceFile $file
    )
    {
        $this->class = new ReflectionClass(UnknownClassType::class);
        $this->initialize();
    }

    /**
     * Get namespace
     */
    public function namespace() : string
    {
        return $this->namespace;
    }

    /**
     * Get source file name
     */
    public function fileName() : string
    {
        return $this->file->name();
    }

    /**
     * Get package directory path
     */
    public function directory() : string
    {
        return $this->packageDirectory;
    }

    <<__Memoize>>
    public function name() : string
    {
        return preg_replace('/^(\w+\\\\)+/', '', $this->fullName());
    }

    /**
     * Get class full name
     */
    <<__Memoize>>
    public function fullName() : string
    {
        $relativeClassName = $this->relativeClassNameFrom($this->fileName());
        $fullClassName = $this->namespace() . '\\' . $relativeClassName;

        return $fullClassName;
    }

    /**
     * Get new instance
     */
    public function instantiate<T>(array<mixed> $parameters = []) : T
    {
        try {
            $instance = $this->class->newInstanceArgs($parameters);
        } catch (Exception $exception) {
            throw new InstantiationException($this->fullName());
        }

        return $instance;
    }

    private function initialize() : void
    {
        try {
            $this->class = new ReflectionClass($this->fullName());
        } catch (ReflectionException $exception) {
            throw new UnknownClassException($this->fullName());
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

    public function isInstantiable() : bool
    {
        return $this->class->isInstantiable();
    }

    private function relativeClassNameFrom(string $file) : string
    {
        $replaceTargets = [
            $this->directory() . '/',
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
