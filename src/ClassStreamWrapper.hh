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

final class ClassStreamWrapper implements StreamWrapper<ClassObject>
{

    public function __construct(
        private ClassObjectStream $classes
    )
    {
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

    public function pipe<To>(Middleware<ClassObject, To> $middleware) : To
    {
        return $middleware->receive($this);
    }

    public function items() : ClassObjectStream
    {
        foreach ($this->classes as $class) {
            yield $class;
        }
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

    public static function fromStream(Stream<ClassObject> $items) : this
    {
        return new static($items);
    }

}
