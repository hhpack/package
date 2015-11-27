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

final class HackSourceFileMathcer implements Matcher<SourceFileName>
{

    public function matches(SourceFileName $item) : bool
    {
        if (preg_match('/^.+\.hh$/', $item) === 0) {
            return false;
        }
        return true;
    }

}
