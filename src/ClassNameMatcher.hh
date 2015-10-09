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

final class ClassNameMatcher implements Matcher<ClassObject>
{

    private string $pattern;

    public function __construct(
        string $pattern
    )
    {
        $this->pattern = '/' . $pattern . '/';
    }

    public function matches(ClassObject $item) : bool
    {
        return preg_match($this->pattern, $item->getShortClassName()) === 1;
    }

    public static function startsWith(string $keyword) : this
    {
        $pattern = '^' . preg_quote($keyword, '/');
        return new ClassNameMatcher($pattern);
    }

    public static function endsWith(string $keyword) : this
    {
        $pattern = preg_quote($keyword, '/') . '$';
        return new ClassNameMatcher($pattern);
    }

}
