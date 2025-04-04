pipeline
{
    agent any
    stages
    {
        stage('Build')
        {
            steps
            {
                echo "Building project in container..."
                sh '''docker build -t my_builder_image -f Dockerfile.build .'''
            }
        }
        stage('Test')
        {
            steps
            {
                echo "Running tests..."
                sh '''
                  mkdir -p /tmp/logs && \
                  docker run --name my_test_run --rm -v /tmp/logs:/logs my_builder_image ./fruit_test && \
                  cp -r /tmp/logs ${WORKSPACE}/logs || true
                '''
            }
        }
        stage('Archive logs') 
        {
            steps 
            {
                echo "Archivizing logs..."
                archiveArtifacts artifacts: 'logs/*.log', fingerprint: true
            }
        }
    }
}
