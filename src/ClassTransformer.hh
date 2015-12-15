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

final class ClassTransformer implements Middleware<SourceFile, StreamObject<ClassObject>>
{

    private PackageNamespace $namespace;
    private DirectoryPath $packageDirectory;

    public function __construct(
        PackageOptions $package
    )
    {
        $this->namespace = (string) $package['namespace'];
        $this->packageDirectory = realpath($package['packageDirectory']);
    }

    public function receive(Stream<SourceFile> $stream) : StreamObject<ClassObject>
    {
        $factory = () ==> {
            $sourceFiles = $stream->items();

            foreach ($sourceFiles as $sourceFile) {
                try {
                    $classObject = new ClassObject(
                        $sourceFile,
                        $this->namespace,
                        $this->packageDirectory
                    );
                } catch (UnknownClassException $exception) {
                    continue;
                }
                yield $classObject;
            }
        };

        return StreamObject::fromStream( $factory() );
    }

    public static function fromOptions(PackageOptions $package) : this
    {
        return new static($package);
    }

}
