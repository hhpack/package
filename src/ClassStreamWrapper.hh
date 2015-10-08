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
        $factory = () ==> {
            foreach ($this->classes as $class) {
                if ($class->implementsInterface($interfaceName) === false) {
                    continue;
                }
                yield $class;
            }
        };
        return static::fromStream( $factory() );
    }

    public function subclassOf(string $className) : ClassStreamWrapper
    {
        $factory = () ==> {
            foreach ($this->classes as $class) {
                if ($class->isSubclassOf($className) === false) {
                    continue;
                }
                yield $class;
            }
        };
        return static::fromStream( $factory() );
    }

    public function startsWith(string $keyward) : ClassStreamWrapper
    {
        $pattern = "/^$keyward/";
        $factory = () ==> {
            foreach ($this->classes as $class) {
                if (preg_match($pattern, $class->getClassName()) !== 1) {
                    continue;
                }
                yield $class;
            }
        };
        return static::fromStream( $factory() );
    }

    public function endsWith(string $keyward) : ClassStreamWrapper
    {
        $pattern = "/$keyward$/";
        $factory = () ==> {
            foreach ($this->classes as $class) {
                if (preg_match($pattern, $class->getClassName()) !== 1) {
                    continue;
                }
                yield $class;
            }
        };
        return static::fromStream( $factory() );
    }

    public function toImmVector() : ImmVector<ClassFile>
    {
        return $this->toVector()->toImmVector();
    }

    public function toVector() : Vector<ClassFile>
    {
        $classes = Vector {};

        foreach ($classes as $class) {
            $classes->add($class);
        }

        return $classes;
    }

    public static function fromStream(ClassFileStream $classes) : ClassStreamWrapper
    {
        return new static($classes);
    }

}
