<?hh //strict

/**
 * This file is part of HHPack\Package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Package;

final class ClassTransformer implements Middleware<SourceFile, ResourceStream<ClassObject>>
{

    private string $name;
    private string $directory;

    public function __construct(
        Pair<string, string> $namespace
    )
    {
        list($this->name, $this->directory) = $namespace;
    }

    public function receive(Stream<SourceFile> $stream) : ResourceStream<ClassObject>
    {
        $factory = () ==> {
            $sources = $stream->items();

            foreach ($sources as $source) {
                $classes = $source->resources()->map(($ref) ==> {
                    return new ClassObject($ref);
                });

                foreach ($classes as $class) {
                    yield $class;
                }
            }
        };

        return ResourceStream::fromItems( $factory() );
    }

    public static function of(Pair<string, string> $namespace) : this
    {
        return new static($namespace);
    }

}
