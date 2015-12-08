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

final class SourceFileStreamWrapper implements StreamWrapper<SourceFile>
{

    public function __construct(
        private SourceFileStream $sources
    )
    {
    }

    public function select(Matcher<SourceFile> $matcher = new AnyMatcher()) : this
    {
        $factory = () ==> {
            foreach ($this->sources as $source) {
                if ($matcher->matches($source) === false) {
                    continue;
                }
                yield $source;
            }
        };
        return static::fromStream( $factory() );
    }

    public function items() : SourceFileStream
    {
        foreach ($this->sources as $source) {
            yield $source;
        }
    }

    public function pipeTo<To>(Middleware<SourceFile, To> $middleware) : To
    {
        return $middleware->receive($this);
    }

    public function toImmVector() : ImmVector<SourceFile>
    {
        return $this->toVector()->toImmVector();
    }

    public function toVector() : Vector<SourceFile>
    {
        $sources = Vector {};

        foreach ($this->sources as $source) {
            $sources->add($source);
        }

        return $sources;
    }

    public static function fromStream(Stream<SourceFile> $items) : this
    {
        return new static($items);
    }

}
