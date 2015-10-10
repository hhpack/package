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

final class SourceFileStreamWrapper implements StreamWrapper<SourceFile>
{

    public function __construct(
        private SourceFileStream $sources
    )
    {
    }

    public function select(Matcher<SourceFile> $matcher) : this
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

    public function startsWith(string $keyword) : this
    {
        return $this->select( SourceFileNameMatcher::startsWith($keyword) );
    }

    public function endsWith(string $keyword) : this
    {
        return $this->select( SourceFileNameMatcher::endsWith($keyword) );
    }

    public function items() : SourceFileStream
    {
        foreach ($this->sources as $source) {
            yield $source;
        }
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

    public static function fromStream(SourceFileStream $sources) : this
    {
        return new static($sources);
    }

}
