<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Package;


final class FileCollector implements Collector<SourceFile, ResourceStream<SourceFile>>
{

    public function __construct(
        private string $directory
    )
    {
    }

    public function collect((function(SourceFile):bool) $matcher = any()) : ResourceStream<SourceFile>
    {
        $factory = () ==> {
            $pattern = realpath($this->directory) . '/*.hh';

            foreach ($this->findFiles($pattern) as $collectedFile) {
                yield new SourceFile($collectedFile);
            }
        };

        return ResourceStream::fromItems( $factory() )->filter($matcher);
    }

    private function findFiles(string $pattern) : Iterator<string>
    {
        foreach (glob($pattern) as $file) {
            yield $file;
        }

        // An error may appear in the check type, do not use the constant.
        // GLOB_NOSORT = 4, GLOB_ONLYDIR = 8192
        $directories = glob(dirname($pattern) . '/*', 4 | 8192);

        foreach ($directories as $directory) {
            $files = $this->findFiles($directory . '/' . basename($pattern));

            foreach ($files as $file) {
                yield $file;
            }
        }
    }

}
