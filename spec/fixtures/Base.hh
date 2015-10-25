<?hh //partial

namespace hhpack\package\spec\fixtures;

class Base
{

    public function __construct(
        private $name = ''
    )
    {
    }

    public function getName() : string
    {
        return $this->name;
    }

}
