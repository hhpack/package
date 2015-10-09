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

final class ClassStreamWrapper implements StreamWrapper<ClassObject>
{

    public function __construct(
        private ClassObjectStream $classes
    )
    {
    }

    public function implementsInterface(string $interfaceName) : this
    {
        return $this->select( ClassTypeMatcher::implementsInterface($interfaceName) );
    }

    public function subclassOf(string $className) : this
    {
        return $this->select( ClassTypeMatcher::subclassOf($className) );
    }

    public function classes() : this
    {
        return $this->select( ClassTypeMatcher::classType() );
    }

    public function abstractClasses() : this
    {
        return $this->select( ClassTypeMatcher::abstractClassType() );
    }

    public function traits() : this
    {
        return $this->select( ClassTypeMatcher::traitType() );
    }

    public function interfaces() : this
    {
        return $this->select( ClassTypeMatcher::interfaceType() );
    }

    public function startsWith(string $keyword) : this
    {
        return $this->select( ClassNameMatcher::startsWith($keyword) );
    }

    public function endsWith(string $keyword) : this
    {
        return $this->select( ClassNameMatcher::endsWith($keyword) );
    }

    public function select(Matcher<ClassObject> $matcher) : this
    {
        $factory = () ==> {
            foreach ($this->classes as $class) {
                if ($matcher->matches($class) === false) {
                    continue;
                }
                yield $class;
            }
        };
        return static::fromStream( $factory() );
    }

    public function toImmVector() : ImmVector<ClassObject>
    {
        return $this->toVector()->toImmVector();
    }

    public function toVector() : Vector<ClassObject>
    {
        $classes = Vector {};

        foreach ($this->classes as $class) {
            $classes->add($class);
        }

        return $classes;
    }

    public static function fromStream(Stream<ClassObject> $classes) : this
    {
        return new static($classes);
    }

}
