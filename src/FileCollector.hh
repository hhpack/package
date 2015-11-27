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

//use \Generator;

final class FileCollector implements Collector<SourceFileStreamWrapper>
{

    public function __construct(
        private DirectoryPath $directory
    )
    {
    }

    public function collect() : SourceFileStreamWrapper
    {
        $factory = () ==> {
            foreach ($this->findFiles($this->directory) as $collectedFile) {
                if ($this->matchFile($collectedFile) === false) {
                    continue;
                }
                yield new SourceFile($collectedFile);
            }
        };

        return SourceFileStreamWrapper::fromStream( $factory() );
    }

    private function matchFile(string $entry) : bool
    {
        if (preg_match('/^.+\.hh$/', $entry) === 0) {
            return false;
        }
        return true;
    }

    private function matchDirectory(string $entry) : bool
    {
        if ($entry === ".." || $entry === ".") {
            return false;
        }
        return true;
    }

    private function findFiles(DirectoryPath $target) : Iterator<SourceFileName>
    {
        $targetDirectory = dir($target);
        $currentDirectory = $target;

        while (false !== ($entry = $targetDirectory->read())) {
            if ($this->matchDirectory($entry) === false) {
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
