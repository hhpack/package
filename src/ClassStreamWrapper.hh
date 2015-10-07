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

final class ClassStreamWrapper
{

    public function __construct(
        private ClassFileStream $classes
    )  
    {
    }

    public function implementsInterface(string $interfaceName) : ClassStreamWrapper
    {
        return static::fromStream($this->_implementsInterface($interfaceName));
    }

    public function isSubclassOf(string $className) : ClassStreamWrapper
    {
        return static::fromStream($this->_isSubclassOf($className));
    }

    private function _implementsInterface(string $interfaceName) : ClassFileStream
    {
        foreach ($this->classes as $class) {
            if ($class->implementsInterface($interfaceName) === false) {
                continue;
            }
            yield $class;
        }
    }

    private function _isSubclassOf(string $className) : ClassFileStream
    {
        foreach ($this->classes as $class) {
            if ($class->isSubclassOf($className) === false) {
                continue;
            }
            yield $class;
        }
    }

    public static function fromStream(ClassFileStream $classes) : ClassStreamWrapper
    {
        return new static($classes);
    }

}
