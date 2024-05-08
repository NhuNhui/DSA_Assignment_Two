def plot_solution(f: Function, x0: Vector, t_max: float, h: float):
  """
  Plot the approximate solution to the ODE dx/dt = f(t, x) using the
  implicit Euler algorithm

  f: 2-dimensional real-vector-valued function
  x0: 2-dimensional real vector (initial value)
  t_max: real number (maximum time)
  h: real number (time step)
  """
  fig, ax = plt.subplots(figsize=(5, 5))
  n = int(t_max / h) + 1
  t = np.linspace(0, t_max, n)
  x = np.zeros((n, 2))
  x[0] = x0
  for i in range(n-1):
    x[i+1] = implicit_euler(f, t[i], x[i], h)
  
  plt.plot(t, x[:,0], label='Romeo')
  plt.plot(t, x[:,1], label='Juliet')
  plt.legend()
  plt.title('LOVE BETWEEN NARCISSISTIC NERDS')
  plt.xlabel('Time')
  plt.ylabel('Love for the other')
  #ax.set_axis_off()
  plt.show()

def plot_phase_portrait(A, x0, t_max, h):
  
    x1 = np.linspace(-5, 5, 20)
    x2 = np.linspace(-5, 5, 20)
    X1, X2 = np.meshgrid(x1, x2)


    U, V = np.zeros(X1.shape), np.zeros(X2.shape)
    for i in range(X1.shape[0]):
        for j in range(X2.shape[1]):
            x = np.array([X1[i,j], X2[i,j]])
            dx = dx_dt(0, x)
            U[i,j], V[i,j] = dx[0], dx[1]
  
    fig, ax = plt.subplots(figsize=(5, 5))
    C = np.sqrt(U**2 + V**2)
    U = U / C
    V = V / C
    ax.quiver(X1, X2, U, V, C, cmap = 'viridis')

    n = int(t_max / h) + 1
    t = np.linspace(0, t_max, n)
    x = np.zeros((n, 2))
    x[0] = x0
    for i in range(n-1):
        x[i+1] = x[i] + h*dx_dt(t[i], x[i])
    
    plt.plot(x[:,0], x[:,1], label = 'Trajectory')
    ax.set_xlim([-5, 5])
    ax.set_ylim([-5, 5])
    ax.set_xlabel('$x_1$')
    ax.set_ylabel('$x_2$')
    ax.set_title('Phase portrait and vector field')
    plt.legend()
    plt.show()  
#Example usage
A = np.array([[1., -1.], [2., 1.]])
x0 = np.array([1., 1.])
t_max = 15.0
h = 0.01

def example0(t: float, x: Vector) -> Vector:
    return A @ x
def dx_dt(t, x):
    return A @ x
plot_solution(example0, x0, t_max, h)
plot_phase_portrait(example0, x0, t_max, h)