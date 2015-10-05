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

use \Generator;

final class FileCollector implements Collector<DirectoryPath, SourceFileVector>
{

    public function collectFrom(DirectoryPath $target) : SourceFileVector
    {
        $packageFiles = Vector {};
        $collectedFiles = $this->findFiles($target);

        foreach ($collectedFiles as $collectedFile) {
            if ($this->matchFile($collectedFile) === false) {
                continue;
            }
            $packageFiles->add($collectedFile);
        }
        return $packageFiles->toImmVector();
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

    private function findFiles(string $target) : Generator<int, SourceFile, void>
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
