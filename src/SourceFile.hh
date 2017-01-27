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

use FredEmmott\DefinitionFinder\FileParser;
use ReflectionClass;

final class SourceFile implements NamedObject
{

    public function __construct(
        private string $name
    )
    {
    }

    public function name() : string
    {
        return $this->name;
    }

    <<__Memoize>>
    public function directory() : string
    {
        return dirname($this->name);
    }

    public function startsWith(string $keyward) : bool
    {
        $pattern = "/^" . preg_quote($keyward, '/') . "/";
        return $this->match($pattern);
    }

    public function endsWith(string $keyward) : bool
    {
        $pattern = "/" . preg_quote($keyward, '/') . "$/";
        return $this->match($pattern);
    }

    public function match(string $pattern) : bool
    {
        return preg_match($pattern, $this->name()) === 1;
    }

    <<__Memoize>>
    public function resources() : ImmVector<ReflectionClass>
    {
        $parser = FileParser::FromFile($this->name);

        $resources = Vector {};
        $resources->addAll($parser->getClassNames());
        $resources->addAll($parser->getInterfaceNames());
        $resources->addAll($parser->getTraitNames());

        return $resources->map(($name) ==> new ReflectionClass($name))
            ->toImmVector();
    }

    public function hasResources() : bool
    {
        return $this->resources()->isEmpty();
    }

}
