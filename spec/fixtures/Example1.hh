<?hh //partial

namespace package\spec\fixtures;

class Example1
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
