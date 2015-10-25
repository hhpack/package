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

use \Exception;

class UnknownClassException extends Exception
{

    public function __construct(
        protected string $className,
        protected int $code = 0,
        protected ?Exception $previous = null
    )
    {
        parent::__construct("Please be $className is sure possible autoload", $code, $previous);
    }

}
