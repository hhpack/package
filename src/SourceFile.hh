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

final class SourceFile implements NamedObject
{

    public function __construct(
        private SourceFileName $name
    )
    {
    }

    public function getName() : string
    {
        return $this->name;
    }

    <<__Memoize>>
    public function getDirectory() : string
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
        return preg_match($pattern, $this->getName()) === 1;
    }

}
