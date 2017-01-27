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

use \ReflectionClass;
use \ReflectionException;

final class VendorNamespace
{

    private string $name;
    private string $directory;

    public function __construct(
        Pair<string, string> $namespace
    )
    {
        list($this->name, $this->directory) = $namespace;
    }

    <<__Memoize>>
    public function name() : string
    {
        $atoms = explode('\\', $this->name);
        $atoms = (new Vector($atoms))->filter((string $atom) ==> {
            return trim($atom) !== '';
        });
        return implode('\\', $atoms);
    }

    public function directory() : string
    {
        return $this->directory;
    }

    public function sources((function(SourceFile):bool) $matcher = any()) : Stream<SourceFile>
    {
        $collector = new FileCollector($this->directory());
        return $collector->collect($matcher);
    }

    public function classes((function(ClassObject):bool) $matcher = any()) : Stream<ClassObject>
    {
        $middleware = ClassTransformer::of(Pair {
            $this->name(),
            $this->directory()
        });
        return $this->sources()->pipeTo($middleware)->filter($matcher);
    }

    public static function of(Pair<string, string> $namespace) : this
    {
        return new static($namespace);
    }

}
