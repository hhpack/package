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
            $sourceFiles = $stream->items();

            foreach ($sourceFiles as $sourceFile) {
                try {
                    $classObject = new ClassObject(
                        $this->name,
                        $this->directory,
                        $sourceFile
                    );
                } catch (UnknownClassException $exception) {
                    continue;
                }
                yield $classObject;
            }
        };

        return ResourceStream::fromItems( $factory() );
    }

    public static function of(Pair<string, string> $namespace) : this
    {
        return new static($namespace);
    }

}
