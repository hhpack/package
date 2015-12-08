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


final class FileCollector implements Collector<Matcher<SourceFile>, NamedObjectStream<SourceFile>>
{

    private NoisePathMatcher $noiseMatcher;
    private HackSourceFileMathcer $sourceMatcher;

    public function __construct(
        private DirectoryPath $directory
    )
    {
        $this->noiseMatcher = new NoisePathMatcher();
        $this->sourceMatcher = new HackSourceFileMathcer();
    }

    public function collect(Matcher<SourceFile> $matcher = new AnyMatcher()) : SourceFileStreamWrapper
    {
        $factory = () ==> {
            foreach ($this->findFiles($this->directory) as $collectedFile) {
                if ($this->sourceMatcher->matches($collectedFile) === false) {
                    continue;
                }
                yield new SourceFile($collectedFile);
            }
        };

        return NamedObjectStream::fromStream( $factory() )->select($matcher);
    }

    private function findFiles(DirectoryPath $target) : Iterator<SourceFileName>
    {
        $targetDirectory = dir($target);
        $currentDirectory = $target;

        while (false !== ($entry = $targetDirectory->read())) {
            if ($this->noiseMatcher->matches($entry)) {
                continue;
            }

            $absoluteFilePath = $currentDirectory . '/' . $entry;

            if (is_file($absoluteFilePath)) {
                yield $absoluteFilePath;
            } else if (is_dir($absoluteFilePath)) {
                $files = $this->findFiles($absoluteFilePath);
                foreach ($files as $file) {
                    yield $file;
                }
            }
        }
        $targetDirectory->close();
    }

}
